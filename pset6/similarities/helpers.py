from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())

# Print matrix in a pretty way
def printm(matrix):
    for lst in matrix:
        print(lst)

def distances(a, b):
    """Calculate edit distance from a to b"""

    # calculate dimensions of matrix
    row = len(a)
    col = len(b)

    # initializing matrix
    matrix = []
    for i in range(0, row + 1):
        matrix.append([])
        for j in range(0, col + 1):
            matrix[i].append((0, None))

    for i in range(1, row + 1):
        matrix[i][0] = (i, Operation.DELETED)

    for j in range(1, col + 1):
        matrix[0][j] = (j, Operation.INSERTED)


    for i in range(1, row + 1):
        for j in range(1, col + 1):

            # Deletion
            deldist = matrix[i-1][j][0] + 1

            # Insertion
            insdist = matrix[i][j-1][0] + 1

            # Substition
            subdist = matrix[i-1][j-1][0] if a[i - 1] == b[j - 1] else matrix[i-1][j-1][0] + 1

            dist = min(deldist, insdist, subdist)

            if (dist == deldist):
                matrix[i][j] = (dist, Operation.DELETED)
            elif (dist == insdist):
                matrix[i][j] = (dist, Operation.INSERTED)
            else:
                matrix[i][j] = (dist, Operation.SUBSTITUTED)

    return matrix
