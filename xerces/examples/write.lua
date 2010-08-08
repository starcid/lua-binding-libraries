require "xerces"

local doc = xerces.parse( [[<testDoc/>]] )
local root = doc:root()

for i = 1, 5 do
    local child = root:append( "testAttribute" )
    child:set_attr( "index", tostring( i ) )
end

for i = 1, 5 do
    local child = root:append( "testText" )
    child:set_text( tostring( i * 10 ) )
end

for i = 1, 5 do
    local child = root:append( "testNode" )
    child:set_attr( "index", tostring( i*100 ) )
    child:set_text( tostring( i * 1000 ) )    
end

doc:save( "xerces_test.xml", true )

