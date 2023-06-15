/*

*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <set>

using namespace std;
    
class Folder;

class Message{
    friend class Folder;
    friend void swap(Message &lhs, Message &rhs);
public:
    explicit Message(const string &str = ""):contents(str){ }
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();
    void save(Folder&);
    void remove(Folder&);

private:
    string contents;
    set<Folder*> folders;
    void add_to_Folders(const Message &);
    void remove_from_Folders();

};

class Folder{
    friend class Message;
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    ~Folder();
    void addMsg(Message* m){
        messages.insert(m);
    }
    void remMsg(Message* m){
        messages.erase(m);
    }
private:
    set<Message*> messages;

};
Folder::Folder(const Folder &f):messages(f.messages){
    for(auto m : messages)
        m->save(*this);
}

Folder::~Folder(){
    for(auto m : messages){
        m->remove(*this);
    }
}

Folder& Folder::operator=(const Folder &f){
    for(auto m : messages){
        m->remove(*this);
    }
    messages = f.messages;
    for(auto m : messages){
        m->save(*this);
    }
    
    return *this; 
}

void Message::save(Folder &f){
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f){
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_Folders(const Message &m){
    for(auto f : m.folders) 
        f->addMsg(this);
}
void Message::remove_from_Folders(){
    for(auto f : folders){
        f->remMsg(this);
    }
}

Message::Message(const Message &m):contents(m.contents), folders(m.folders){
    add_to_Folders(m);
}

//Message 析构函数
Message::~Message(){                                                                                            
    remove_from_Folders();
}

//Message 赋值重载
Message& Message::operator=(const Message &rhs){
    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

void swap(Message &lhs, Message &rhs){
    using std::swap;
    for(auto f : lhs.folders){
        f->remMsg(&lhs);
    }
    for(auto f : rhs.folders){
        f->remMsg(&rhs);
    }

    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    for(auto f : lhs.folders){
        f->addMsg(&lhs);
    }
    for(auto f : rhs.folders){
        f->addMsg(&rhs);
    }
}