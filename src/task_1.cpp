#include <ros/ros.h>
#include <task_1/ParityOfDet.h>
#include "std_msgs/Float32.h"
#include <sstream>

// Объявление издателя и подписчика
ros::Publisher pub;
ros::Subscriber sub;

// Переменная для записи имени топика
std::string topic_name;

// Частота отправки сообщений в топик
const double frequency = 10.0;

// Обработчик подписчика
void parity(const std_msgs::Float32 msg_determinant)
{
    if (int(msg_determinant.data) % 2 == 0)
//        ROS_INFO_STREAM("Subscriber: even /" << topic_name);
        ROS_INFO_STREAM("even"); 
    else
//        ROS_INFO_STREAM("Subscriber: odd /" << topic_name);
        ROS_INFO_STREAM("odd");       
}


// Обработчик сервиса
bool srv_handler(task_1::ParityOfDet::Request &req,
                 task_1::ParityOfDet::Response &res)
{
//    ROS_INFO("request: a11=%d, a12=%d, a13=%d, "
//                      "a21=%d, a22=%d, a23=%d, "
//                      "a31=%d, a32=%d, a33=%d, ",
//                       req.a11, req.a12, req.a13,
//                       req.a21, req.a22, req.a23,
//                       req.a31, req.a32, req.a33);

    // Вычисляем определитель
    int det = req.a11 * (req.a22 * req.a33 - req.a23 * req.a32) -
              req.a12 * (req.a21 * req.a33 - req.a23 * req.a31) +
              req.a13 * (req.a21 * req.a32 - req.a22 * req.a31);

    res.det = (float) det;
//    ROS_INFO_STREAM("Service output: %f", res.det);

    ros::Rate rate(frequency);

    // Объявление и инициализация объекта сообщения
    std_msgs::Float32 msg_det;
    msg_det.data = (float) det;

//    ROS_INFO_STREAM("Publish to topic /" << topic_name << " determinant: %f", msg_det.data);

    // Отправляем сообщение в топик
    pub.publish(msg_det);
    rate.sleep();

    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "task_1");
    ros::NodeHandle n;
//    ROS_INFO("Starting task_1...");

    // Записываем значение имени топика
    n.param<std::string>("topic_determinant", topic_name, "determinant");

    // Инициализация издателя и подписчика
    pub = n.advertise<std_msgs::Float32>(topic_name, 100);
    sub = n.subscribe(topic_name, 100, parity);

    ros::ServiceServer service = n.advertiseService("parity_of_det", srv_handler);
//    ROS_INFO("Ready to work...");
    ros::spin();

    return 0;
}
