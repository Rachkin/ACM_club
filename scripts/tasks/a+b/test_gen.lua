TESTS = {}
COUNT = 3
for i = 1, COUNT do
    TESTS[i] = {}
end

TEST_NUM = 1

INPUT = ""
OUTPUT = ""

TESTS[1] = {
    input= "2 3",
    output = "5"
}

TESTS[2] = {
    input= "200 301",
    output = "501"
}

TESTS[3] = {
    input= "205 301",
    output = "506"
}