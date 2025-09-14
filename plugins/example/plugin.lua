function OnInit(ctx)
  local n = ctx:getState()
  ctx:setState(10)
  local m = ctx:getState()
  print("[Lua] Values are "..n.." and "..m)
end

function OnCleanup(ctx)
  print("[Lua] Cleaning up!")
end
