import queue
class Elem:
    def __init__(self,x):
        self.data=x

    def __lt__(self,other):
        return self.data>other.data

q = queue.PriorityQueue()
q.put(Elem(111))
q.put(Elem(222))
print(q.get().data)
print(q.get().data)
# q.put(11)
# q.put(22)
# q.put(33)
# print(q.get())
# print(q.get())
# print(q.get())