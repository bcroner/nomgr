# NOMGR
CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -I.

CORE  = sat2.cpp structural_check.cpp vault_check.cpp triggerable.cpp
VOTES = vote.cpp

TESTS = sat2_test trade_check_test vault_check_test structural_check_test \
        triggerable_test market_test vote_test producer_vote_test \
        session_test rollback_test

.PHONY: all test clean bench
all: nomgr

nomgr: NOMGR.cpp $(CORE)
	$(CXX) $(CXXFLAGS) -o $@ $^

sat2_test: sat2.cpp sat2_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

trade_check_test: sat2.cpp trade_check.cpp trade_check_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

vault_check_test: sat2.cpp vault_check.cpp vault_check_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

structural_check_test: sat2.cpp structural_check.cpp structural_check_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

triggerable_test: $(CORE) triggerable_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

market_test: NOMGR.cpp $(CORE) market_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

vote_test: $(VOTES) vote_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

producer_vote_test: $(VOTES) producer_vote.cpp producer_vote_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

session_test: $(VOTES) session.cpp session_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

rollback_test: $(VOTES) rollback.cpp rollback_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(TESTS)
	@fail=0; \
	for t in $(TESTS); do \
	  ./$$t || fail=1; \
	done; \
	if [ $$fail -eq 0 ]; then echo "ALL SUITES PASSED"; else echo "SUITE FAILURES"; exit 1; fi

bench: sat2.cpp bench.cpp
	$(CXX) $(CXXFLAGS) -o bench $^

clean:
	rm -f nomgr bench $(TESTS) *.exe *.o build.log
