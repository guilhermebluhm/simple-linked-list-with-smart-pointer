#include <iostream>

class pokemon{
public:

    std::string name;
    int uid;

    pokemon(std::string n, int id){
        this->name = n;
        this->uid = id;
    }


};

struct node{

    std::shared_ptr<pokemon> p_object;
    std::shared_ptr<node> proximo;

};

class linkedList{

private:
    std::shared_ptr<node> head;
public:

    linkedList(){
        this->head = nullptr;
    }

    void deletePokemonWithUid(int uid){

        if(head == nullptr){
            std::cout << "list empty nothing exists here";
            return;
        }

        std::shared_ptr<node> tmp = head;
        std::shared_ptr<node> actual = head->proximo;

        while (actual != nullptr){

            if(actual->p_object->uid == uid){

                tmp->proximo = actual->proximo;
                actual = nullptr;
                return;
            }

            tmp = actual;
            actual = actual->proximo;

        }

    }

    void deletedOnTail(){

        if(head == nullptr){
            std::cout << "list empty nothing exists here";
            return;
        }

        /*
         *
         * list => null         2       3
         *         *prev_last   *prev   *actual
         *         while
         *         2            3       nullptr
         *         when deleted action
         *         *prev_last -> prox = nullptr(3)
         */

        std::shared_ptr<node> prev_to_last = nullptr;
        std::shared_ptr<node> prev = head;
        std::shared_ptr<node> actual = head->proximo;

        while(actual != nullptr){

            prev_to_last = prev;
            prev = actual;
            actual = actual->proximo;

        }

        if(prev_to_last == nullptr){
            head = nullptr;
        }
        else{
            prev_to_last->proximo = nullptr;
        }

    }

    void deletedOnHead(){

        if(head == nullptr){
            std::cout << "list empty nothing exists here";
            return;
        }

        std::shared_ptr<node> tmp = head;
        head = head->proximo;
        tmp = nullptr;

    }

    bool checkExist(std::shared_ptr<pokemon> p){

        std::shared_ptr<node> tmp = std::make_shared<node>();
        tmp = head;

        while(tmp != nullptr){

            if(p->uid == tmp->p_object->uid){
                std::cout << "already exists this pokemon\n";
                return true;
            }

            tmp = tmp->proximo;

        }

        return false;
    }

    void insertNodeOnTail(std::string name, int uid){

        std::shared_ptr<node> newnode = std::make_shared<node>();
        newnode->p_object = std::make_shared<pokemon>(name, uid);
        newnode->proximo = nullptr;

        if(head == nullptr){
            head = newnode;
        }
        else{

            std::shared_ptr<node> tmp = std::make_shared<node>();
            tmp = nullptr;

            std::shared_ptr<node> actual = std::make_shared<node>();
            actual = head;

            while (actual != nullptr){

                tmp = actual;
                actual = actual->proximo;

            }

            tmp->proximo = newnode;

        }

    }

    void insertNodeOnHead(std::shared_ptr<pokemon> pok){

        if(checkExist(pok)){
            return;
        }

        std::shared_ptr<node> newnode = std::make_shared<node>();

        newnode->p_object = std::make_shared<pokemon>(pok->name, pok->uid);
        newnode->proximo = nullptr;

        if(head == nullptr){
            head = newnode;
        }
        else{
            newnode->proximo = head;
            head = newnode;
        }

    }

    void printLinkedList(){
        if(head == nullptr){
            std::cout << "empty list";
        }
        else{
            while (head != nullptr){
                std::cout << "pokemon name: " << (*head).p_object->name << " uid: "
                          << (*head).p_object->uid << std::endl;
                head = head->proximo;
            }
        }
    }
};

int main() {
    linkedList l{};
    std::shared_ptr<pokemon> pok1 = std::make_unique<pokemon>("pikachu",1251);
    std::shared_ptr<pokemon> pok2 = std::make_unique<pokemon>("bulbasauro",1255);
    l.insertNodeOnHead(pok1);
    l.insertNodeOnHead(pok2);
    l.insertNodeOnHead(pok2);
    l.insertNodeOnTail("charmander",1296);
    l.deletedOnHead();
    l.deletePokemonWithUid(1296);
    l.printLinkedList();
    return 0;
}
