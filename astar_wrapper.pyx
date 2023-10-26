cdef extern from "AStar.h":
    cdef cppclass AStar:
        AStar(vector[vector[int]] grid)
        bint findPath(self, int startX, int startY, int goalX, int goalY)

cdef class PyAStar:
    cdef AStar* astar

    def __cinit__(self, grid):
        self.astar = new AStar(grid)

    def find_path(self, int startX, int startY, int goalX, int goalY):
        return self.astar.findPath(startX, startY, goalX, goalY)
