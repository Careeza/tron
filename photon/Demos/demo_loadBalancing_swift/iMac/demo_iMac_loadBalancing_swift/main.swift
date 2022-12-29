import Foundation

class App : DemoView
{
	var networkLogic : NetworkLogic!
	
	func help()
	{
		print("\n")
		print("0 - exit")
		print("1 - connect (when disconnected)")
		print("1 - create game or join random (outside a game room)")
		print("1 - leave game (inside a game room)")
		print("2 - disconnect")
		print("h - or any other key to print this help page")
		networkLogic.updateState()
	}
	
	init()
	{
		print("Swift iMac Demo")
		networkLogic = NetworkLogic(demoView : self)

		help()
		
		var exit = false
		while(!exit)
		{
			networkLogic.service()

			let ch = getcharIfKbhit()
			if (ch != -1)
			{
				print("")
				switch(ch)
				{
				case -1:
					break
				case 48:
					print("exit")
					exit = true
					break
				case 48 + 1:
					networkLogic.onButton()
					break
				case 48 + 2:
					networkLogic.onButton2()
					break
				default:
					help()
					break
				}
			}
			usleep(100000)
		}
	}
	
	func write(_ s : String)
	{
		print(s)
	}
	
	func log(_ s : String)
	{
		print(s)
	}	
	
	func showState(_ state : Int, stateStr : String, roomName : String, playerNr : Int32, inLobby : Bool, inRoom : Bool)
	{
		if (inRoom)
		{
			print(stateStr, roomName, "/", playerNr)
		}
		else
		{
			print(stateStr)
		}
	}
}

_ = App()
