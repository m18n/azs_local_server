#pragma once
#include "local_data.h"
#include "view.h"

class azs {
private:
    crow::App<AuthVerefy,DatabaseVerefy> app;
    local_data ld;
    mysql_conn_info mysql_info;
    model::azs_database azs_db;
public:
    azs()
    {
        //init crow
        init_view_login(app);
        init_web(&azs_db,&ld);
        crow::mustache::set_global_base("site");
        crow::mustache::set_base("site");
        
        //init db
        mysql_info=ld.get_mysql_conn_info();
        mysql_info.show();
        bool conn=azs_db.connect(mysql_info);
        if(!conn){
            std::cout<<"DONT CONNECT\n";
        }
    }
    void start()
    {
        std::cout << "START SERVER\n";
        app.port(3000).run();
    }
};