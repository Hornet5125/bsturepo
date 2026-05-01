import unittest
def Sort_Binary_Strings(strings):
    if not type( strings ) is list:
        raise TypeError
    arr = []
    for s in strings:
        if s[0:2] != "0b":
            raise ValueError
        arr.append( int( s[2:], 2 ) )
    for i in range( len( arr ) - 1 ):
        for j in range( len( arr ) - 1 - i ):
            if arr[ j ] > arr[ j + 1 ]:
                arr[ j ], arr[ j + 1 ] = arr[ j + 1 ], arr[ j ]
                strings[ j ], strings[ j + 1 ] = strings[ j + 1 ], strings[ j ]
    return strings
class TestSolution( unittest.TestCase ):
    def test_sort_exception1( self ):
        with self.assertRaises( TypeError ):
            Sort_Binary_Strings( 1 )
    def test_sort_exception2( self ):
        with self.assertRaises( TypeError ):
            Sort_Binary_Strings( [ 1, 2, 3 ] )
    def test_sort_exception3( self ):
        with self.assertRaises( ValueError ):
            Sort_Binary_Strings( [ "0101010" ] )
    def test_sort_1( self ):
        self.assertListEqual( Sort_Binary_Strings( [ "0b01", "0b00", "0b11", "0b10" ] ), [ "0b00", "0b01", "0b10", "0b11" ] )
    def test_sort_2( self ):
        self.assertListEqual( Sort_Binary_Strings( [] ), [] )
if __name__ == '__main__':
    n = int( input() )
    arr = []
    for i in range( n ):
        arr.append( input() )
    Sort_Binary_Strings( arr )
    unittest.main()
