import os

from tictactoe import State, Status, available_moves, check, move, print_board


def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")


game = State()
turn = 1
while True:
    status = check(game)
    if status != Status.IN_PROGRESS:
        print("\n")
        print_board(game)
        print("\n")
        match status:
            case Status.x:
                print("X wins")
            case Status.o:
                print("O wins")
            case Status.DRAW:
                print("Draw")
        break
    print("\n")
    print_board(game)
    print("\n")
    print(available_moves(game))
    print("\n")
    if turn:
        p1 = int(input("Player 1: "))
        assert p1 in range(9)
        game = move(game, p1, 1)
        turn = not (turn)
    else:
        p2 = int(input("Player 2: "))
        assert p2 in range(9)
        game = move(game, p2, 0)
        turn = not (turn)
