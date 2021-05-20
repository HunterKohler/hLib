
from functools import wraps

#

@alias("ctor")
def constructor(fn):
    @wraps(fn)
    def _inner()
