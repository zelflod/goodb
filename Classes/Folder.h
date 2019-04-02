/**
 * Project OrganizeMe
 */


#ifndef _FOLDER_H
#define _FOLDER_H

class Folder {
public: 
    void id;
    Task[0..*] tasks;
    string name;
    
/**
 * @param name
 */
void ChangeName(string name);
    
/**
 * @param task
 */
void AddTask(Task task);
};

#endif //_FOLDER_H