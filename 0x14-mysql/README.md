# 0x14. MySQL
- [x] DevOps
- [x] SysAdmin
- [x] MySQL

![My Sql](https://s3.amazonaws.com/intranet-projects-files/holbertonschool-sysadmin_devops/280/KkrkDHT.png)

## Resources
* What is a primary-replica cluster
* MySQL primary replica setup
* Build a robust database backup strategy

### man or help:
* ```mysqldump```

## Learning Objectives
* What is the main role of a database
* What is a database replica
* What is the purpose of a database replica
* Why database backups need to be stored in different physical locations
* What operation should you regularly perform to make sure that your database backup strategy actually works

The MySQL server provides a database management system with querying and connectivity capabilities, as well as the ability to have excellent data structure and integration with many different platforms.

## Needed Knowledge

- [What is a primary-replica cluster](https://www.digitalocean.com/community/tutorials/how-to-choose-a-redundancy-plan-to-ensure-high-availability#sql-replication)

- [MySQL primary replica setup](https://www.digitalocean.com/community/tutorials/how-to-set-up-replication-in-mysql)

- [Build a robust database backup strategy](https://www.databasejournal.com/ms-sql/developing-a-sql-server-backup-strategy/)

- `mysqldump`

## Installation Guide for mysql 5.7.*

- First go to site [dev.mysql.com](https://dev.mysql.com/doc/refman/5.7/en/checking-gpg-signature.html) and copy the PGP PUBLIC KEY just immediately under the _Notice_ section to your clipboard.

- Create a new file in your terminal with a .key extension and paste the PGP PUB KEY copied to clipboard.
- Then do the following

```bash
$ sudo apt-key add name_of_file.key
OK

# adding it to the apt repo
$ sudo sh -c 'echo "deb http://repo.mysql.com/apt/ubuntu bionic mysql-5.7" >> /etc/apt/sources.list.d/mysql.list'

# updating the apt repo to add the url i added earlier
$ sudo apt-get update

# now check your available versions
$ sudo apt-cache policy mysql-server
mysql-server:
  Installed: (none)
  Candidate: 8.0.31-0ubuntu0.20.04.2
  Version table:
     8.0.31-0ubuntu0.20.04.2 500
        500 http://us-east-1.ec2.archive.ubuntu.com/ubuntu focal-updates/main amd64 Packages
     8.0.31-0ubuntu0.20.04.1 500
        500 http://security.ubuntu.com/ubuntu focal-security/main amd64 Packages
     8.0.19-0ubuntu5 500
        500 http://us-east-1.ec2.archive.ubuntu.com/ubuntu focal/main amd64 Packages
     5.7.40-1ubuntu18.04 500
        500 http://repo.mysql.com/apt/ubuntu bionic/mysql-5.7 amd64 Packages

# Now am installing mysql 5.7.*
$ sudo apt-get install -f mysql-client=5.7* mysql-community-server=5.7* mysql-server=5.7* -y
```
## Project Task

### Creating a user and Granting Priviledges in mysql
```mysql
$ mysql -root -p
Password:	/* Type root password

mysql> CREATE USER 'holberton_user'@'localhost' IDENTIFIED BY 'projectcorrection280hbtn';

mysql> GRANT REPLICATION CLIENT ON *.* TO 'holberton_user'@'localhost';

mysql> FLUSH PRIVILEGES;
```

### Creating Database, Tables and adding Data to the Tables

```mysql

mysql> CREATE DATABASE db_name_;

-- To verify if db is created
mysql> SHOW DATABASES;

mysql> USE db_name;

mysql> CREATE TABLE table_name (
    -> col_1 data_type,
    -> col_2 data_type);
-- continue adding more coloums to your taste for me i just added two coloumns

mysql> INSERT INTO table_name VALUES (val_1, val_2);

-- Verify if data was added succesfully do
mysql> SELECT * FROM tb_name;

-- Grant SELECT priviledges
GRANT SELECT ON database_name.table_name TO 'holberton_user'@'localhost';
e.g
GRANT SELECT ON tyrell_corp.nexus6 TO 'holberton_user'@'localhost';
```

### Setting Up MySQL Replication

- First create replication user and grant replication priviledge ( best practice).

```mysql

mysql> CREATE USER 'replica_user'@'%' IDENTIFIED BY 'replica_user_pwd';

mysql> GRANT REPLICATION SLAVE ON *.* TO 'replica_user'@'%';

mysql> GRANT SELECT ON mysql.user TO 'holberton_user'@'localhost';

-- to verify
mysql> SELECT user, Repl_slave_priv FROM mysql.user;

mysql> exit
```
- Next up you go to the /etc/mysql/mysql.conf.d/mysqld.cnf and comment the bind address and then add this lines to it

```bash
# By default we only accept connections from localhost
# bind-address = 127.0.0.1
server-id = 1
log_bin = /var/log/mysql/mysql-bin.log
binlog_do_db = db_name
```
- Then you enable incoming connection to port 3306 and restart mysql-server
```bash

$ sudo ufw allow from 'replica_server_ip'(web-02) to any port 3306

$ sudo service mysql restart/sudo systemctl restart mysql
```
- Now log back in to mysql-server to lock db and prepare binary file for replication.

```bash
$ mysql -uroot -p
password:
```
```mysql
mysql>

mysql> FLUSH TABLES WITH READ LOCK;(Locks tables)....After show master and importing files(dump),  write UNLOCK TABLES;(to unlock the tables).

mysql> SHOW MASTER STATUS;
e.g.;
+------------------+----------+--------------+------------------+-------------------+
| File             | Position | Binlog_Do_DB | Binlog_Ignore_DB | Executed_Gtid_Set |
+------------------+----------+--------------+------------------+-------------------+
| mysql-bin.000001 |      149 | db           |                  |                   |
+------------------+----------+--------------+------------------+-------------------+

```
_Take note of the binary log and the position, jot it down or you leave this window open and you open another window to continue_

- you then export the db from myql-server to local machine and then copy this db to replica machine

```bash
$ mysqldump -uroot -p db_name > export_db_name.sql
i.e, sudo mysqldump -u root -p tyrell_corp > tyrell_corp.sql

$ scp -i _idenetity_file_ export_db_name.sql user@machine_ip:location(here, i used the 0-transfer_file[web-server] to move file to other servers)
```
- Then ssh to replica machine ip_adress to import this tables to replica mysql-server

```bash

$ mysql -uroot -p
password:


mysql> CREATE DATABASE db_name;

mysql>exit
bye

$ mysql -uroot -p db_name < export_db_name.sql
-- i.e, sudo mysqldump -uroot -p tyrell_corp < /tmp/tyrell_corp.sql
password:

# Now edit the config file in /etc/mysql/mysql.conf.d/mysqld.cnf and then reload mysql-server

```bash

server-id = 2
log_bin = /var/log/mysql/mysql-bin.log
binlog_do_db = db_name_from_master_mysql-server
relay_log = /var/log/mysql/mysql-relay-bin.log

$ sudo service mysql restart
```

- Login to mysql server in replica to configure replication

```bash

$ mysql -uroot -p
password:


mysql>
```
```mysql

mysql> CHANGE MASTER TO
    -> MASTER_HOST='web-01 IP',
    -> MASTER_USER='replication_user_name',(i.e 'replica_user')
    -> MASTER_PASSWORD='replication_password',(own_password)
    -> MASTER_LOG_FILE='recorded_log_file_name',(e.g, mysql-bin.000001)
    -> MASTER_LOG_POS=recorded_log_position;(e.g, 154)

SHOW SLAVE STATUS\G;

-- Then you start slave
mysql> START SLAVE;(or STOP SLAVE when necessary)
```
When done, back in the servers, restart firewall and mysql.
__That's it you've configured replication on mysql, do reach out for any further assistance__
