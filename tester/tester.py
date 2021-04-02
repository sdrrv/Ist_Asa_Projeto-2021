import os
algo = r"./mainv2.cpp"
testingCode = r"./projeto1.cpp"
randomGen = r"./randomDAG.cpp"

direct = "./data"


def compile():
    print("COMPILING" + "-#"*30)
    # algo compiler
    os.system(f"g++ -std=c++11 -O3 -Wall {algo} -lm -o algo.out")
    # testingCode compiler
    os.system(f"g++ -std=c++11 -O3 -Wall {testingCode} -lm -o testingCode.out")
    # randomGen compiler
    os.system(f"g++ -std=c++11 -O3 -Wall {randomGen} -lm -o randomGen.out")
    print("-#"*30)


def populateInput(testInput, vertices, connections):
    os.system(f"g++ -std=c++11 -O3 -Wall {randomGen} -lm -o randomGen.out")
    os.system(f"./randomGen.out {vertices} {connections} > {testInput}")


def test(iter, vertices, connections):
    compile()
    os.system(f"touch {direct}/Algo.out")
    os.system(f"touch {direct}/TestingCode.out")
    for i in range(iter):
        print(i)
        testInput = (direct+"/"+f"Input{i}.in")
        os.system(f"touch {testInput}")
        populateInput(testInput, vertices, connections)
        os.system(f"./algo.out < {testInput} >> {direct}/Algo.out")
        os.system(
            f"./testingCode.out < {testInput} >> {direct}/TestingCode.out")


def main():
    iter = input("Times to Iterate: ")
    vertices = input("Vetices to create: ")
    connections = input("Prob of forming connections: ")
    test(int(iter), int(vertices), float(connections))
    return 0


main()
