/**
 * Project OrganizeMe
 */


#ifndef _USER_H
#define _USER_H

class User {
public: 
    void id;
    void login;
    void password;
    
/**
 * @param login
 * @param passwordHash
 */
void Login(string login, string passwordHash);
    
void Logout();
    
/**
 * @param newLogin
 */
void ChangeLogin(string newLogin);
    
/**
 * @param newPasswordHash
 */
void ChangePassword(string newPasswordHash);
};

#endif //_USER_H