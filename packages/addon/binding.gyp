{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "src/addon.cpp"
      ],
      "include_dirs": [ 
        "/usr/include/",
        "/usr/include/boost/",
        "../../3rd/ruby-1.8.7",
        "/run/media/home/common/gabrielmartins.dev/dev/cpp/orm-xp/orm-node/packages/core/include"
      ], 
      "libraries": [
        # "-L../../3rd/ruby-1.8.7",
        "-L/usr/lib", 
        "-lboost_system",
        "-lboost_filesystem",
        "-lboost_atomic",
        "-lboost_serialization",
        "-lboost_json",
        "-lboost_json",
        "/run/media/home/common/gabrielmartins.dev/dev/cpp/orm-xp/orm-node/packages/core/lib/libORM-Core.a" 
      ]
    }
  ]
}