
#include <ros/ros.h>
#include <sensor_msgs/BatteryState.h>

#include <iostream>
#include <fstream>
#include "sqlite3.h"

sensor_msgs::BatteryState battery_state_;

void batteryStateCallback(const sensor_msgs::BatteryState::ConstPtr& batteryState) {
    battery_state_ = *batteryState;
    
}

static int dbCallback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
int connectToDatabase(const char* database, sqlite3* db_handle) {
   char *error = 0;
   sqlite3_open(database, &db_handle);
   char *connectionSql = "CREATE TABLE IF NOT EXISTS datos(id int primary_key not null, valor text not null, fecha text default(datetime('now')))";
   int exec = sqlite3_exec(db_handle, connectionSql, dbCallback, 0, &error);
   if (exec != SQLITE_OK) {
      std::cout << "Ocurrió un error al conectar la base de datos" << std::endl;
      sqlite3_free(error);
      return 0;
   } else { 
      std::cout << "Se ha abierto e inicializado correctamente la base de datos" << std:endl;
      return 1;
   }

}

ros::Subscriber batteryStateSub;

int main(int argc, char** argv) {
   sqlite3 *db_handle;
   char *sql;
   char * errorMsg = 0;
   char *database = "basededatos.db";
   int result = connectToDatabase(database, &db_handle);
   if (result == 0) return ROS_INFO_STREAM("Ha fallado la conexión con la base de datos");
   std::cout << "Inicializando nodo de ROS" << std::endl;
   ros::init(argc, argv, "sensor_ufro_node");
   ros::NodeHandle nh;
   std::cout << "Suscrbiendo tópicos" << std::endl;
   batteryStateSub = nh.subscribe("dji_osdk_ros/battery_state",10,&batteryStateCallback);

   ros::Duration(3).sleep(); // Sleep 3 segundos
   ros::AsyncSpinner spinner(4); // 4 threads
   spinner.start();

   int ciclos = 0;
   int max_ciclos = 10;

   while (ciclos < max_ciclos) {
    std::cout << "Counter = " << ciclos << ":\n";
    std::cout << "-------\n";

    ROS_INFO("battery Info :");
    ROS_INFO("battery's capacity: %f", battery_state_.capacity);
    ROS_INFO("battery's voltage: %f", battery_state_.voltage);
    ROS_INFO("battery's current: %f", battery_state_.current);
    ROS_INFO("battery's percentage : %f\n", battery_state_.percentage);
    std::cout << "-------\n\n";
    ros::Duration(3).sleep();
    ciclos += 1;
  }
  std::cout << "Done printing!\n";
  ROS_INFO_STREAM("Finished. Press CTRL-C to terminate the node");
  sqlite3_close(db_handle);
  ros::waitForShutdown();
  return 0;
}


