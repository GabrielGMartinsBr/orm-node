class WriteAndRead
    def initialize(targetPath, action, index)
      read(targetPath) if action == 'readIndexes'
      readFile(targetPath, index.to_i) if action == 'readFile'
    end
  
    def read(targetPath)
      @data = Utils::load(targetPath)
      emitIndexes();
    end
  
    def readFile(targetPath, index)
      @data = Utils::load(targetPath)
      emitFile(index);
    end
  
    def emitIndexes()
      i = 0
      arr = []
      while i < @data.length
        arr[i] = stringfyData(@data[i])
        i += 1
      end
      STDOUT.puts sprintf('data:[%s]', arr.join(','))
      STDOUT.flush
    end
  
    def emitFile(index)
      STDOUT.puts Utils::inflate(@data[index][2])
      STDOUT.flush
    end
  
    def stringfyData(data)
      arr = [
        data[0], 
        sprintf('"%s"', data[1])
      ]
      return sprintf('[%s]', arr.join(','))
    end
end
  
WriteAndRead.new(ARGV[0], ARGV[1], ARGV[2])