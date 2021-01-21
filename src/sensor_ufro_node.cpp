
#include <ros/ros.h>
#include <sensor_msgs/BatteryState.h>

#include <iostream>
#include <fstream>
#include "sqlite3.h"

sensor_msgs::BatteryState battery_state_;

void batteryStateCallback(const sensor_msgs::BatteryState::ConstPtr& batteryState) {
    battery_state_ = *batteryState;
    
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

ros::Subscriber batteryStateSub;

int main(int argc, char** argv) {
    ros::init(argc, argv, "sensor_ufro_node");
    sqlite3 *db_handle;
    char *sql;
    char * errorMsg = 0;

    sqlite3_open("basedatos.db", &db_handle);
    ROS_INFO_STREAM("Se abrió la base de datos");
    sql = "CREATE TABLE DATOS("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "VALOR           TEXT    NOT NULL," \
      "FECHA           TEXT     NOT NULL);";

    int exec = sqlite3_exec(db_handle, sql, callback, 0, &errorMsg);
    if( exec != SQLITE_OK ){
      ROS_INFO_STREAM(errorMsg);
      sqlite3_free(errorMsg);
   } else {
      ROS_INFO_STREAM("Tabla creada correctamente");
   }
   
    ros::NodeHandle nh;
    batteryStateSub = nh.subscribe("dji_osdk_ros/battery_state",10,&batteryStateCallback);
    if (!ros::ok()) sqlite3_close(db_handle);
    ROS_INFO_STREAM("Voltaje bateria: " << battery_state_.voltage, ", Carga de bateria: " << battery_state_.charge);
    ros::spin();
    return 0;

}
