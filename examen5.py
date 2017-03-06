def algorithm(array, k, e):
    value=findkth(array,k)
    print("K is: "+str(value))
    solution = []
    for i in range(0,len(array)):
        if(not(array[i]==value) and abs(value-array[i])<e):
            solution.append(array[i])
    for i in range(0, len(solution)):
        print solution[i]
    return

def findkth(array, k):
    min = 100;
    index = 0;
    solution = []
    while(index < k):
        for i in range(0,len(array)):
            if(array[i] < min and not(array[i] in solution)):
                min = array[i]
        solution.append(min)
        min = 100
        index+=1
    return solution[k-1]

array = [6,3,4,8,7]
algorithm(array, 2, 2)
