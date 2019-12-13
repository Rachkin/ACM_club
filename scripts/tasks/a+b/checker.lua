function check(test)



    RESULT = ""
    if (string.match(OUTPUT, "%s" + TESTS[TEST_NUM].output + "%s" == nil) then
        RESULT = "WA"
    else
        RESULT = "OK"
    end
end
