import os

from tictactoe import Player, State, Status, available_moves, check, move, print_board


# Functionally the same as minimax but some branching is reduced.
def negamax(state: State, player: Player, alpha=-float("inf"), beta=float("inf")):
    global calls
    calls += 1
    best_score = [None, -float("inf")]
    status = check(state)
    if status != Status.IN_PROGRESS:
        match status:
            case Status.x:
                return [None, 1 if player == 1 else -1]
            case Status.o:
                return [None, 1 if player == 0 else -1]
            case Status.DRAW:
                return [None, 0]
    preferred = [4, 0, 2, 6, 8, 1, 3, 5, 7]
    moves = available_moves(state)
    for choice in preferred:
        if choice in moves:
            next_state = move(state, choice, player)
            _, score = negamax(next_state, 1 - player, -beta, -alpha)  # type: ignore
            score = -score
            if score > best_score[1]:
                best_score = [choice, score]
            alpha = max(score, alpha)
            if alpha >= beta:
                break
    return best_score


if __name__ == "__main__":
    calls = 0

    def clear_screen():
        os.system("cls" if os.name == "nt" else "clear")

    first = input("want to go first? [Y/n]").lower()
    game = State()
    if first in ("", "y"):
        turn = 1
    else:
        turn = 0
    while True:
        status = check(game)
        print(status)
        if status != Status.IN_PROGRESS:
            print(status)
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
        print("\n")
        if turn:
            p1 = int(input("You: "))
            assert p1 in range(9)
            game = move(game, p1, 1)
            turn = not (turn)
        else:
            p2 = negamax(game, 0)[0]
            assert p2 in range(9)
            game = move(game, p2, 0)
            turn = not (turn)

    print(f"recursive calls = {calls}")
