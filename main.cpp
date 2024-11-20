#include <iostream>
#include "headers/JSON_Class.hpp"

using namespace std;

vector<string> pathParser(string &str)
{
        vector<string> path;
        char *bucpath = strtok(str.c_str(), '\\');
        while (bucpath)
        {
                path.push_back(bucpath);
                bucpath = strtok(NULL, '\\');
        }
        return path;
}

int main()
{
        JSON jsoninstance;

        string line;
        while (getline(cin, line))
        {
                stringstream streamstr(line);
                string command, path, value;
                cin >> command;
                cin >> path;
                pathParser(path);
                if (command == "set")
                {
                        str >> value;
                }
                else if(command = "get")
                {
                        cout<<get<int>(jsoninstance[path]);
                }
        }
        // jsoninstance.set({"marco","polo","gelu"},42);
        // jsoninstance.set({"1","2","3"},50);

        cout << jsoninstance[{"1", "2", "3"}];

        jsoninstance.closeDB();

        return 0;
}