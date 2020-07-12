py_binary(
  name="server",
  srcs=["server.py"],
  data=[":data"],
  srcs_version="PY3ONLY",
  python_version="PY3",
)

filegroup(
  name="data",
  srcs=["index.html", "index.js", "dist/greeter.js"],
  data=["index.html", "index.js", "dist/greeter.js"],
)

