function OnInit(ctx)
  local n = ctx:getState()
  ctx:setState(10)
  local m = ctx:getState()
  print("Values are "..n.." and "..m)
end
