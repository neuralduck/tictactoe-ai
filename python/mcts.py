import os
import random
from dataclasses import dataclass, field
from math import log, sqrt

from tictactoe import Player, State, Status, available_moves, check, move, print_board


@dataclass
class Node:
    state: State
    player: Player
    parent: "Node | None" = None
    children: dict[int, "Node"] = field(default_factory=dict)
    visits: int = 0
    value: float = 0.0


def uct(child: Node):
    if child.visits == 0:
        return float("inf")
    return child.value / child.visits + 1.414 * sqrt(
        log(child.parent.visits + 1) / child.visits  # type: ignore
    )


def select(node: Node) -> Node:
    while (node.children) and (len(node.children) == len(available_moves(node.state))):
        node = max(node.children.values(), key=uct)
    return node


def expand(node: Node) -> Node:
    if check(node.state) != Status.IN_PROGRESS:
        return node
    for m in available_moves(node.state):
        if m not in node.children:
            nextstate = move(node.state, m, node.player)
            node.children[m] = Node(nextstate, int(not (node.player)), node)  # type: ignore
            return node.children[m]
    return node


def rollout(state: State, player: Player) -> float:
    while True:
        status = check(state)
        if status != Status.IN_PROGRESS:
            match status:
                case Status.x:
                    return 1
                case Status.o:
                    return -1
                case Status.DRAW:
                    return 0
        m = random.choice(available_moves(state))
        state = move(state, m, player)
        player = int(not (player))  # type: ignore


def backprop(node: Node, result: float, player: Player):
    while node:
        node.visits += 1
        if player == node.player:
            node.value += result
        else:
            node.value -= result
        node = node.parent  # type: ignore


def mcts(state: State, player: Player, iterations: int = 1000):
    root = Node(state, player)
    for _ in range(iterations):
        leaf = select(root)
        child = expand(leaf)
        result = rollout(child.state, child.player)
        backprop(child, result, player)
    return max(root.children.items(), key=lambda kv: kv[1].visits)[0]


if __name__ == "__main__":

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
            p2 = mcts(game, 0)
            assert p2 in range(9)
            game = move(game, p2, 0)
            turn = not (turn)
