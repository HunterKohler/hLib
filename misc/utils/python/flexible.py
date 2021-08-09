class _FlexibleBase:
    def __init__(self, *args, **kwargs):
        self.__dict__.update(*args, **kwargs)

    # defines main functionality
    def __getattr__(self, name):        return None
    def __setattr__(self, name, item):  self.__dict__.__setitem__(name, item)
    def __delattr__(self, name):        self.__dict__.__delitem__(name)

    # relies on get/set/del attr
    def __getitem__(self, name):        return self.__getattribute__(name)
    def __setitem__(self, name, item):  return self.__setattr__(name, item)
    def __delitem__(self, name):        return self.__delattr__(name)

    def __contains__(self, name):       return name in self.__dict__
    def __iter__(self):                 yield from self.__dict__.__iter__()
    def __len__(self):                  return self.__dict__.__len__()
    def __repr__(self):                 return self.__dict__.__repr__()

    def __eq__(self, other):
        return (self.__class__ is other.__class__
            and self.__dict__ == other.__dict__)

    @staticmethod
    def getkeys(flexible):
        yield from flexible

    @staticmethod
    def getvalues(flexible):
        for k in flexible:
            yield flexible[k]

    @staticmethod
    def getitems(flexible):
        for k in flexible:
            yield k, flexible[k]


class Flexible(_FlexibleBase):
    pass
