
def rpi_bazel_repository(name):
  native.local_repository(
    name = name,
    path = "../../../rpi_bazel",
  )
   # commit = "65e9ae275849108b0fce7328d91e7c24b39f28c2"
   # http_archive(
   #     name = name,
   #     url = "https://github.com/mjbots/rpi_bazel/archive/{}.zip".format(commit),
   #     sha256 = "d478c502df0d87d3bdff12a024d2ea138af055e47515b00dfd9271be6cf3e290",
   #     strip_prefix = "rpi_bazel-{}".format(commit),
   # )

