/**
 * Project OrganizeMe
 */


#ifndef _PROJECT_H
#define _PROJECT_H

class Project {
public: 
    void id;
    void tagList;
    void admin;
    
/**
 * @param name
 */
void ChangeName(string name);
    
/**
 * @param tag
 */
void AddTag(Tag tag);
};

#endif //_PROJECT_H