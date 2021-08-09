from typing import Callable


# can be used as a decorator
class Functor:
    def __init__(self, __call__: Callable):
        self.__call__ = __call__
