from petrone.drone import Drone




if __name__ == '__main__':

    ROLL = 0
    PITCH = 0
    YAW = 0
    THROTTLE = 0
    drone = Drone(True, True, True, True, True)
    drone.setEventHandler(DataType.UpdateInformation, eventUpdateInformation)

    drone.connect()
    sleep(1)
    if drone.isConnected():