import os
algo = r""
testingCode = r""
randomgen = r""


def compile():
    # algo compiler
    os.system(f"g++ -std=c++11 -O3 -Wall {algo} -lm -o algo.out")
    # testingCode compiler
    os.system(f"g++ -std=c++11 -O3 -Wall {testingCode} -lm -o testingCode.out")


def test(iter, vertices, connections):
    compile()
    for i in range(iter):
        direct = (f"./data/{i}")
        testInput = (direct+"/"+"Input.in")
        os.system(f"mkdir {direct}")
        os.system(f"touch {testInput}")


def main():
    iter = input("Times to Iterate: ")
    vertices = input("Vetices to create: ")
    connections = input("Prob of forming connections: ")
    test(int(iter), int(vertices), float(connections))
    return 0


main()
