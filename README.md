This solution is fully encapsulated in the Serialize and Deserialize functions so as not to create entities. 
During deserialization the links between nodes are fully restored. 
Algorithmic complexity is kept at a level less than quadratic.
No new fields were added to the classes, only language adaptation. The code is completely written in C++. 
The only assumption I allowed myself in order to reduce the algorithmic complexity is that the algorithm implies uniqueness of data in all nodes. 
The uniqueness check is also omitted, because it would increase the algorithmic complexity of algorithms or add new fields and methods to classes. 

The external library nlohmann/json was used to work with json-files, because such functionality is not included in the standard C++ libraries.
Only read/write functions from the library were used.

Example of code usage:

	int main()
	{

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


    std::string filename = "./json2.json";
    list.Serialize(filename);
    std::cout << "List serialized to file: " << filename << std::endl;


    ListRand deserializedList;
    deserializedList.Deserialize(filename);
    std::cout << "List deserialized from file: " << filename << std::endl;


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
