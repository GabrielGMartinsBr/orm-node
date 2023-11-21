class Writer
    def initialize(target, dest)
      @targetPath = target
      @destPath = dest || 'Scripts.rxdata'
      read()
    end
  
    def read()
      indexesFilePath = sprintf('%s/indexes.csv', @targetPath)
      indexes = []
      cursor = 0
      File.open(indexesFilePath, 'r') do |f|
        f.each_line do |line|
          arr = line.strip().split(',')
          content = readFile(cursor, arr[1])
          indexes[cursor] = [arr[0], arr[1], content]
          cursor += 1
        end
      end
      Utils::save(@destPath, indexes);
    end
  
    def readFile(index, name)
      filePath = sprintf('%s/%i-%s.rb', @targetPath, index, name)
      File.open(filePath, 'r') do |f|
        return Zlib::Deflate.deflate(f.read())
      end
    end
    
  end
    
  Writer.new(ARGV[0], ARGV[1])