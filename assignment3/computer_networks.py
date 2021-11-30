# The original topology given in the question.

N = int(input("Enter your value: "))
D=[]
for i in range(N):          # A for loop for row entries
    a =[]
    for j in range(N):      # A for loop for column entries
         a.append(int(input()))
    D.append(a)
nodes=['A','B','C','D','E']

x = int(input())
y = int(input())
# the value taken by me to show that the node is unreachable (16 is generally taken to show that node is unreachable.).
inf=16
# initial status showing which node is reachable from which node and the distance between them.
matrix=[]
i=0
for i in range(N):
  a=D[i]
  for j in range(N):
    if(j==i):
      a[j]=0
    elif(a[j]==0):
      a[j]=inf
  matrix.append(a)

# a 5X5X5 matrix to store the path between every node to every node.   

graph=[]
i=0
j=0
k=0
for i in range(N):
  a=[]
  for j in range(N):
    b=[]
    for k in range(N):
      if(k==i):
        b.append(1)
      elif(D[i][k]==1 and j==k):
        b.append(-1)
      else:
        b.append(0)
    a.append(b)
  graph.append(a)
  

# this function simply checks if every function is reachable from every function or not.
def check_stability(matrix):
  rows=len(matrix)
  columns=len(matrix[0])
  flag=0
  for i in range(rows):
    for j in range(columns):
      if(matrix[i][j]==inf):
        flag=1
  if(flag==1):
    return 0
  else:
    return 1

# Part -1    
i=0
t=0
rows=len(matrix)
columns=len(matrix[0])
while(1):
  for i in range(N):
    for k in range(N):
      if(D[i][k]==1 and i!=k):
        for l in range(N):
          if(matrix[k][l]>matrix[i][l]+1):
            matrix[k][l]=matrix[i][l]+1
            intermediate=[]
            for p in range(N):
              if(p!=k):
                graph[k][l][p]=0
            for p in range(N):
              if(graph[i][l][p]>0):
                intermediate.append(p)
            graph[k][l][l]=-1
            #print(intermediate)
            for tt in intermediate:
              graph[k][l][tt]=2

  t=t+1
  print(matrix,' Time =',t)
  ans=check_stability(matrix)
  if(ans):
    break

# Part -2
t=t+1

print(matrix,' Time =',t)
# Now BC link break as a result we now have to work on the routing table 
t=t+1
D[x][y]=0
D[y][x]=0
# Update the matrix i.e the routing tables of B and C
matrix[x][y]=inf
matrix[y][x]=inf
graph[x][y][y]=inf
graph[y][x][x]=inf
# updated the graph for nodes B and C for other intermediate nodes.
for i in range(N):
  if graph[x][i][y]>1:
    graph[x][i][y]=0
    matrix[x][i]=inf
    graph[x][i][i]=0
  if graph[y][i][x]>1:
    graph[y][i][x]=0
    graph[y][i][i]=0
    matrix[y][i]=inf

print(matrix,' Time =',t)
def check_split_horizon(i,k,l):
  if(graph[i][l][k]>0 and graph[l][l][k]==0):
    graph[i][l][k]=0
    graph[i][i][k]=0
    matrix[i][l]=inf
    return 0
  else:
    return 1
# now information exchange begins again but now split horizon needs to be taken care of as well so use the graph list designed.
while(1):
  for i in range(N):
    for k in range(N):
      if(D[i][k]==1 and i!=k):
        for l in range(N):
          if(matrix[k][l]>matrix[i][l]+1):
            re=check_split_horizon(i,k,l)
            # no split horizon
            if(re):
              matrix[k][l]=matrix[i][l]+1
              intermediate=[]
              for p in range(N):
                if(p!=k):
                  graph[k][l][p]=0
              for p in range(N):
                if(graph[i][l][p]>0):
                  intermediate.append(p)
              graph[k][l][l]=-1
              #print(intermediate)
              for tt in intermediate:
                graph[k][l][tt]=2
            else:
              print("Split horizon between",nodes[i],nodes[k],nodes[l])
  t=t+1
  print(matrix,' Time =',t)
  ans=check_stability(matrix)
  if(ans):
    break