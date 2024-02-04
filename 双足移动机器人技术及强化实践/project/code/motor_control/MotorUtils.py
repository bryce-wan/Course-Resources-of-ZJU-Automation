from MotorControlShell import *

class MotorUtils:
    def __init__(self, port, baudrate):
        self.mce = MotorControlExtend(port, baudrate)
        self.baudrate_dict = {
            "19200": 1,
            "57600": 2,
            "115200": 3,
            "2250000": 4,
            "4500000": 5
        }

    
    def search_motor(self):
        id_list = list()
        for id in range(1, 248):
            if self.mce.ping(id):
                id_list.append(id)
        
        return id_list
    
    
    def set_origin(self, id):
        self.mce.set_origin(id)

    
    def change_baudrate(self, id, baudrate):
        self.mce.write_baudrate(id, self.baudrate_dict[baudrate])

    
    def change_id(self, id, new_id):
        self.mce.write_motor_id(id, new_id)

    
    def save_parameters(self, id):
        self.mce.save_parameters(id)
    

if __name__ == "__main__":
    motor_utils = MotorUtils("COM8", 2250000)

    # change motor id and baudrate
    motor_utils.change_id(3, 10)
    motor_utils.change_baudrate(3, "2250000")
    motor_utils.save_parameters(1)

    # search motor and set origin
    id_list = motor_utils.search_motor()
    print(id_list)

    for id in id_list:
        motor_utils.set_origin(id)
        motor_utils.save_parameters(id)