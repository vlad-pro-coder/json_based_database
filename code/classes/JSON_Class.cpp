#include "../../headers/JSON_Class.hpp"

using namespace std;

JSON::JSON():
        FreeTable(TableAllocFile = getFileDescriptors("AllocTableFile")),
        IndexFinder(existingIndexes = ReadIndexFile(indexesFile = getFileDescriptors("indexes")))
{
        root = make_shared<NestedMaps>();
        jsonDBFile = getFileDescriptors("DBfile");

        ReadNodeData(1, existingIndexes, jsonDBFile, root);
}

shared_ptr<NestedMaps> JSON::create_instance()
{
        shared_ptr<NestedMaps> test = make_shared<NestedMaps>();
        test->data = unordered_map<string, shared_ptr<NestedMaps>>();
        test->isLoaded = 1;
        test->id = -1;
        test->updated = 1;
        return test;
}

void JSON::set(const vector<string> &path, variant<bool,int,string,double,long long> value)
{
        shared_ptr<NestedMaps> current = root;
        for (size_t i = 0; i < path.size(); i++)
        {
                if (!current->isLoaded)
                        ReadNodeData(current->id, existingIndexes, jsonDBFile, current);
                auto &map = get<unordered_map<string, shared_ptr<NestedMaps>>>(current->data);
                if (i == path.size() - 1)
                {
                        if (map[path[i]] == nullptr)
                                map[path[i]] = create_instance();
                        map[path[i]]->data = value;
                        map[path[i]]->updated = 1;
                }
                else
                {
                        if (map.find(path[i]) == map.end())
                        {
                                map[path[i]] = create_instance();
                                current->updated = 1;
                        }

                        current = map[path[i]];
                }
        }
}

variant<bool,int,string,double,long long> JSON::getValue(const vector<string> &path) const
{
        shared_ptr<NestedMaps> current = root;
        for (size_t i = 0; i < path.size(); i++)
        {
                if (!current->isLoaded)
                        ReadNodeData(current->id, existingIndexes, jsonDBFile, current);
                auto &map = get<unordered_map<string, shared_ptr<NestedMaps>>>(current->data);
                if (map.find(path[i]) == map.end())
                        throw out_of_range("Key not found in path. " + to_string(i));
                current = map[path[i]];
        }
        if (!current->isLoaded)
                ReadNodeData(current->id, existingIndexes, jsonDBFile, current);
        return current->data;
}

variant<bool,int,string,double,long long> JSON::operator[](const vector<string> &path) const
{
        return getValue(path);
}

void JSON::closeDB()
{
        save_DB(root, "");
        save_indexes(existingIndexes);
        save_freeMemTable(FreeTable.allocTable);

        close(jsonDBFile.FileDesc);
        close(indexesFile.FileDesc);
        close(TableAllocFile.FileDesc);

        exit(0);
}