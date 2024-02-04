import pyd.MotorControl as pyd


class MotorControl(pyd.MotorControl):
    def __init__(self, port, baudrate):
        super().__init__(port, baudrate)

    def check_id(self, motor_id: int):
        super().check_id(motor_id)

    def read_servo_state(self, motor_id: int) -> bool:
        return super().read_servo_state(motor_id)

    def write_servo_state(self, motor_id: int, state: bool):
        super().write_servo_state(motor_id, state)

    def read_running_state(self, motor_id: int) -> bool:
        return super().read_running_state(motor_id)

    def return_home(self, motor_id: int):
        super().return_home(motor_id)

    def stop(self, motor_id: int):
        super().stop(motor_id)

    def read_position_output(self, motor_id: int) -> int:
        return super().read_position_output(motor_id)

    def read_position_motor(self, motor_id: int) -> int:
        return super().read_position_motor(motor_id)

    def write_position(self, motor_id: int, position: int, velocity: int):
        super().write_position(motor_id, position, velocity)


class MotorControlExtend(pyd.MotorControlExtend):
    def __init__(self, port, baudrate):
        super().__init__(port, baudrate)

    def ping(self, motor_id: int) -> bool:
        return super().ping(motor_id)

    def read_motor_id(self, motor_id: int) -> int:
        return super().read_motor_id(motor_id)

    def write_motor_id(self, motor_id: int, id: int):
        super().write_motor_id(motor_id, id)

    def read_baudrate(self, motor_id: int) -> int:
        return super().read_baudrate(motor_id)

    def write_baudrate(self, motor_id: int, baudrate: int):
        super().write_baudrate(motor_id, baudrate)

    def set_origin(self, motor_id: int):
        super().set_origin(motor_id)

    def save_parameters(self, motor_id: int):
        super().save_parameters(motor_id)
