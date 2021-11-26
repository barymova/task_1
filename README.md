# task_1
It's the answer to the first task in the ROS course 
____
Чтобы запустить, используйте следующие команды:

В первом окне терминала:

    roscore

Во втором окне терминала:

    source devel/setup.bash

    rosrun task_1 task_1

В третьем окне терминала:

    source devel/setup.bash

    rosservice call /parity_of_det ...

В четвертом окне терминала:

    rostopic echo determinant

_Чтобы при работе с узлом выводилась дополнительная информация, можно раскомментировать некоторые строки в файле task_1._
