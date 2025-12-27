import os

from tictactoe import Player, State, Status, available_moves, check, move, print_board


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
    for choice in available_moves(state):
        next_state = move(state, choice, player)
        _, score = negamax(next_state, 1 - player, -beta, -alpha)  # type: ignore
        score = -score
        if score > best_score[1]:
            best_score = [choice, score]
        alpha = max(score, alpha)
        if alpha >= beta:
            break
    return best_score


def minimax(state: State, player: Player, alpha=-float("inf"), beta=float("inf")):
    global calls
    calls += 1
    match player:
        case 1:
            best_score = [None, -float("inf")]
        case 0:
            best_score = [None, float("inf")]
    status = check(state)
    if status != Status.IN_PROGRESS:
        match status:
            case Status.x:
                return [None, 1]
            case Status.o:
                return [None, -1]
            case Status.DRAW:
                return [None, 0]
    for choice in available_moves(state):
        next_state = move(state, choice, player)
        _, score = minimax(next_state, int(not (player)), alpha, beta)  # type: ignore
        if (player == 1) and (score > best_score[1]):
            best_score = [choice, score]
            # alpha = max(alpha, best_score[1])
            # if alpha >= beta:
            #     break
        if (player == 0) and (score < best_score[1]):
            best_score = [choice, score]
            # beta = min(beta, best_score[1])
            # if beta <= alpha:
            #     break
    return best_score


if __name__ == "__main__":
    calls = 0

    def clear_screen():
        os.system("cls" if os.name == "nt" else "clear")

    game = State()
    turn = 1
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
            p1 = int(input("Player 1: "))
            assert p1 in range(9)
            game = move(game, p1, 1)
            turn = not (turn)
        else:
            p2 = negamax(game, 0)[0]
            assert p2 in range(9)
            game = move(game, p2, 0)
            turn = not (turn)

    print(f"recursive calls = {calls}")
