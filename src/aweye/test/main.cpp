/***************************************************************
    Copyright: 2013, Robert Morin

    This file is part of Aweye.

    Aweye is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Aweye is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Aweye.  If not, see <http://www.gnu.org/licenses/>.

 **************************************************************/
// see : http://stackoverflow.com/questions/3546054/how-do-i-run-a-single-test-with-unittest

/// @todo if you have a lot of time to lose, correct CHECK_EQUAL expected and actual...

#include <UnitTest++.h>
#include <TestReporterStdout.h>

int main()
{
    // change if you want to run a single suite or test
    std::string suite = "";
    std::string test = "";
    if( suite != "" || test != "")
    {
        const UnitTest::TestList& allTests( UnitTest::Test::GetTestList() );
        UnitTest::TestList selectedTests;
        UnitTest::Test* p = allTests.GetHead();
        while( p )
        {
            if(p->m_details.suiteName == suite)
            {
                if (test == "" || p->m_details.testName == test)
                {
                    selectedTests.Add( p );
                }
            }
            UnitTest::Test* q = p;
            p = p->next;
            q->next = NULL;
        }

        //run selected test(s) only
        UnitTest::TestReporterStdout reporter;
        UnitTest::TestRunner runner( reporter );
        return runner.RunTestsIf( selectedTests, 0, UnitTest::True(), 0 );
    }
    else
    {
        return UnitTest::RunAllTests();
    }
}
