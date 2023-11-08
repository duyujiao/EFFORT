package org.example.ioc_02;

public class UserService {
    
    private UserDao userDao;

    public UserService(UserDao userDao) {
        this.userDao = userDao;
    }
}