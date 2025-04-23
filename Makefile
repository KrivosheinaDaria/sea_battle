all: main clean
main: main.o Ship.o Ship_Manager.o Game_Field.o Double_Damage.o Scanner.o Bombing.o Ability_Manager.o Ship_Error.o Attack_Error.o File.o Game_State.o Game.o
	g++ main.o Ship.o Ship_Manager.o Game_Field.o Double_Damage.o Scanner.o Bombing.o Ability_Manager.o Ship_Error.o Attack_Error.o File.o Game_State.o Game.o -o main
main.o: main.cpp Ship.h Ship_Manager.h Game_Field.h Ability_Manager.h File.h Game_State.h Game.h
	g++ -c main.cpp
Ship.o: Ship.cpp Ship.h
	g++ -c Ship.cpp
Ship_Manager.o: Ship_Manager.cpp Ship.h Ship_Manager.h
	g++ -c Ship_Manager.cpp
Game_Field.o: Game_Field.cpp Ship.h Game_Field.h Ship_Error.h
	g++ -c Game_Field.cpp
Double_Damage.o: Double_Damage.cpp Double_Damage.h Special_Abilities.h
	g++ -c Double_Damage.cpp
Scanner.o: Scanner.cpp Scanner.h Special_Abilities.h
	g++ -c Scanner.cpp
Bombing.o: Bombing.cpp Bombing.h Special_Abilities.h
	g++ -c Bombing.cpp
Ability_Manager.o: Ability_Manager.cpp Ability_Manager.h Double_Damage.h Scanner.h Bombing.h
	g++ -c Ability_Manager.cpp
Ship_Error.o: Ship_Error.cpp Ship_Error.h
	g++ -c Ship_Error.cpp
Attack_Error.o: Attack_Error.cpp Attack_Error.h
	g++ -c Attack_Error.cpp
File.o: File.cpp File.h Game_State.h Ship.h
	g++ -c File.cpp
Game_State.o: Game_Field.cpp File.h Game_State.h
	g++ -c Game_State.cpp
Game.o: Game.cpp Game.h
	g++ -c Game.cpp
clean:
	rm -rf *.o