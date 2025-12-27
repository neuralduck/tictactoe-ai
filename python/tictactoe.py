from dataclasses import dataclass
from enum import Enum
from typing import Literal


class Status(Enum):
    x = 1
    o = 0
    DRAW = 2
    IN_PROGRESS = 3


@dataclass(frozen=True)
class State:
    x: int = 0b000000000
    o: int = 0b000000000


Player = Literal[1, 0]


def move(state: State, choice: int, player: Player) -> State:
    choice = 1 << choice
    assert not ((state.x | state.o) & choice)
    match player:
        case 1:
            return State(x=state.x | choice, o=state.o)
        case 0:
            return State(x=state.x, o=state.o | choice)


def check(state):
    horizontal = 0b111000000
    vertical = 0b100100100
    diag1 = 0b100010001
    diag2 = 0b001010100
    draw = 0b111111111
    for i in (0, 3, 6):
        if state.x & (horizontal >> i) == (horizontal >> i):
            return Status.x
        if state.o & (horizontal >> i) == (horizontal >> i):
            return Status.o
    for i in (0, 1, 2):
        if state.x & (vertical >> i) == (vertical >> i):
            return Status.x
        if state.o & (vertical >> i) == (vertical >> i):
            return Status.o
    if (state.x & diag1 == diag1) or (state.x & diag2 == diag2):
        return Status.x
    if (state.o & diag1 == diag1) or (state.o & diag2 == diag2):
        return Status.o
    if draw == state.x | state.o:
        return Status.DRAW
    return Status.IN_PROGRESS


def available_moves(state: State):
    not_occupied = ~(state.x | state.o)
    empty = not_occupied & 0b111111111
    return list(filter(lambda i: (empty & (1 << i)), range(9)))


def print_board(state: State):
    board = [" " for _ in range(9)]
    for i in range(9):
        if state.x & (1 << i):
            board[i] = "x"
        elif state.o & (1 << i):
            board[i] = "o"
    ref = "0|1|2\n3|4|5\n6|7|8\n\n"
    board_string = f"{board[0]}|{board[1]}|{board[2]}\n{board[3]}|{board[4]}|{board[5]}\n{board[6]}|{board[7]}|{board[8]}"
    print(ref + board_string)


"""
b 8 7 6 5 4 3 2 1 0
x 0 0 0 0 0 1 0 0 0
o 0 0 0 0 0 0 0 0 0
"""
