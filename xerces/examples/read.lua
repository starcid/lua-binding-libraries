require "xerces"

local doc = xerces.open ( "xerces_test.xml" )
local root = doc:root()

for k,v in pairs(root:children()) do
    if v:type() == xerces.ELEMENT_NODE then
        if v:name() == "testAttribute" then
            print( v:name(), v:attribute( "index" ) )
            elseif v:name() == "testText" then
            print( v:name(), v:text() )
            elseif v:name() == "testNode" then
            print( v:name(), v:attribute( "index" ), v:text() )
        end
    end
end
