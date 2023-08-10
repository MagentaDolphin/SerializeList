#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ListNode
{
public:
    ListNode* Prev;
    ListNode* Next;
    ListNode* Rand;
    std::string Data;

    ListNode() : Prev(nullptr), Next(nullptr), Rand(nullptr) {}
};

class ListRand
{
public:
    ListNode* Head;
    ListNode* Tail;
    int Count;

    ListRand() : Head(nullptr), Tail(nullptr), Count(0) {}

    void Serialize(const std::string& filename)
    {
        json j;
        ListNode* node = Head;

        while (node != nullptr)
        {
            json nodeJson;
            nodeJson["Data"] = node->Data;

            if (node->Prev != nullptr)
                nodeJson["Prev"] = node->Prev->Data;
            else
                nodeJson["Prev"] = nullptr;

            if (node->Next != nullptr)
                nodeJson["Next"] = node->Next->Data;
            else
                nodeJson["Next"] = nullptr;

            if (node->Rand != nullptr)
                nodeJson["Rand"] = node->Rand->Data;
            else
                nodeJson["Rand"] = nullptr;

            j.push_back(nodeJson);
            node = node->Next;
        }

        std::ofstream file(filename);
        file << j.dump(4);
        file.close();
    }

    void Deserialize(const std::string& filename)
    {
        std::ifstream file(filename);
        json j;
        file >> j;
        file.close();

        std::map<std::string, ListNode*> nodeMap;

        // Создание всех узлов списка без связей
        for (const auto& nodeJson : j)
        {
            ListNode* node = new ListNode();
            node->Data = nodeJson["Data"].get<std::string>();
            node->Prev = nullptr;
            node->Next = nullptr;
            node->Rand = nullptr;

            nodeMap[node->Data] = node;

            if (Head == nullptr)
            {
                Head = node;
                Tail = node;
            }
            else
            {
                Tail->Next = node;
                node->Prev = Tail;
                Tail = node;
            }

            Count++;
        }

        // Восстановление связей между узлами
        for (const auto& nodeJson : j)
        {
            ListNode* node = nodeMap[nodeJson["Data"].get<std::string>()];

            if (!nodeJson["Prev"].is_null())
                node->Prev = nodeMap[nodeJson["Prev"].get<std::string>()];

            if (!nodeJson["Next"].is_null())
                node->Next = nodeMap[nodeJson["Next"].get<std::string>()];

            if (!nodeJson["Rand"].is_null())
                node->Rand = nodeMap[nodeJson["Rand"].get<std::string>()];
        }
    }
};

int main()
{
    // Пример использования
    ListRand list;
    ListNode* node1 = new ListNode();
    ListNode* node2 = new ListNode();
    ListNode* node3 = new ListNode();
    ListNode* node4 = new ListNode();
    ListNode* node5 = new ListNode();
    ListNode* node6 = new ListNode();

    node1->Data = "Node1";
    node2->Data = "Node2";
    node3->Data = "Node3";
    node4->Data = "Node4";
    node5->Data = "Node5";
    node6->Data = "Node6";

    node1->Next = node2;
    node2->Prev = node1;
    node2->Next = node3;
    node3->Prev = node2;
    node3->Next = node4;
    node4->Prev = node3;
    node4->Next = node5;
    node5->Prev = node4;
    node5->Next = node6;
    node6->Prev = node5;
    

    node1->Rand = node3;
    node2->Rand = node1;
    node3->Rand = node2;
    node4->Rand = node6;
    node5->Rand = node5;
    node6->Rand = node4;

    list.Head = node1;
    list.Tail = node6;
    list.Count = 6;

    // Сериализация списка
    std::string filename = "./json2.json";
    list.Serialize(filename);
    std::cout << "List serialized to file: " << filename << std::endl;

    // Десериализация списка
    ListRand deserializedList;
    deserializedList.Deserialize(filename);
    std::cout << "List deserialized from file: " << filename << std::endl;

    // Проверка восстановленного списка
    ListNode* node = deserializedList.Head;
    while (node != nullptr)
    {
        std::cout << "Node data: " << node->Data << std::endl;

        if (node->Prev != nullptr)
            std::cout << "Prev node data: " << node->Prev->Data << std::endl;

        if (node->Next != nullptr)
            std::cout << "Next node data: " << node->Next->Data << std::endl;

        if (node->Rand != nullptr)
            std::cout << "Rand node data: " << node->Rand->Data << std::endl;

        std::cout << std::endl;
        node = node->Next;
    }

    return 0;
}
