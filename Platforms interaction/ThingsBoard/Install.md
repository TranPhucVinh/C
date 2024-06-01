# Step 1. Install Java 11 (OpenJDK)
ThingsBoard service is running on Java 11 so OpenJDK 11 is required:
```sh
sudo apt update
sudo apt install openjdk-11-jdk
```
Configure your operating system to use OpenJDK 11 by default. You can configure which version is the default using the following command:
```sh
sudo update-alternatives --config java
```
Check the installation: ``java -version``
# Step 2. ThingsBoard service installation
Download installation package.
```sh
wget https://github.com/thingsboard/thingsboard/releases/download/v3.5.1/thingsboard-3.5.1.deb
```
Install ThingsBoard as a service
```sh
sudo dpkg -i thingsboard-3.5.1.deb
```
# Step 3. Configure ThingsBoard database

## PostgreSQL installation and setup on Raspbian

```sh
# import the repository signing key:
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -

# add repository contents to your system:
RELEASE=$(lsb_release -cs)
echo "deb http://apt.postgresql.org/pub/repos/apt/ ${RELEASE}"-pgdg main | sudo tee  /etc/apt/sources.list.d/pgdg.list

# install and launch the postgresql service:
sudo apt update
sudo apt -y install postgresql
sudo service postgresql start
```
Once PostgreSQL is installed, you need to create a new user or set the password for the the main user:
```sh
pi@raspberrypi:~/Downloads $ sudo service postgresql start
pi@raspberrypi:~/Downloads $ sudo su - postgres

SSH is enabled and the default password for the 'pi' user has not been changed.
This is a security risk - please login as the 'pi' user and type 'passwd' to set a new password.

postgres@raspberrypi:~$ 
postgres@raspberrypi:~$ psql
psql (13.11 (Raspbian 13.11-0+deb11u1))
Type "help" for help.

postgres=# \password #setup password
Enter new password for user "postgres": 
Enter it again: 
postgres=# 
postgres=# \q #quit
postgres@raspberrypi:~$ 
```
Then, press “Ctrl+D” to return to main user console and connect to the database to create thingsboard DB:
```sh
psql -U postgres -d postgres -h 127.0.0.1 -W
CREATE DATABASE thingsboard;
\q
```
## ThingsBoard Configuration
Edit ThingsBoard configuration file
```sh
sudo nano /etc/thingsboard/conf/thingsboard.conf
```
Add the following lines add the end of the configuration file:
```sh
# DB Configuration 
export DATABASE_TS_TYPE=sql
export SPRING_DATASOURCE_URL=jdbc:postgresql://localhost:5432/thingsboard
export SPRING_DATASOURCE_USERNAME=postgres
export SPRING_DATASOURCE_PASSWORD=PUT_YOUR_POSTGRESQL_PASSWORD_HERE #Add the PostreSQL password setup before here
# Specify partitioning size for timestamp key-value storage. Allowed values: DAYS, MONTHS, YEARS, INDEFINITE.
export SQL_POSTGRES_TS_KV_PARTITIONING=MONTHS
```
**Note**: Special care for **SPRING_DATASOURCE_PASSWORD** as you have put your PostreSQL password setup before here
# Step 4. Choose ThingsBoard queue service
ThingsBoard uses queue services for API calls between micro-services and able to use next queue services: In Memory (default), AWS SQS, Google Pub/Sub or Azure Service Bus.

In Memory queue is built-in and enabled by default. No additional configuration steps required.

# Step 5. Memory update for slow machines (1GB of RAM)
Edit ThingsBoard configuration file
```sh
sudo nano /etc/thingsboard/conf/thingsboard.conf
```
Add the following lines to the configuration file.
```sh
# Update ThingsBoard memory usage and restrict it to 256MB in /etc/thingsboard/conf/thingsboard.conf
export JAVA_OPTS="$JAVA_OPTS -Xms256M -Xmx256M"
```
# Step 6. Run installation script
Once ThingsBoard service is installed and DB configuration is updated, you can execute the following script:
```sh
# --loadDemo option will load demo data: users, devices, assets, rules, widgets.
sudo /usr/share/thingsboard/bin/install/install.sh --loadDemo
```
Wait for it to finish installing, that might take a few minutes

# Step 7. Start ThingsBoard service
Execute the following command to start ThingsBoard:

```sh
sudo service thingsboard start
```
Once started, you will be able to open Web UI using the following link:
```sh
http://localhost:8080/
```
By default, only ``System Administrator`` with email sysadmin@thingsboard.org and password ``sysadmin`` are available.
