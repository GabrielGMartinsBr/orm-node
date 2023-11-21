require 'zlib'

module Utils
  def save(filename, obj)
    File.open(filename, "wb") { |f|
      Marshal.dump(obj, f);
    }
  end

  def load(filename)
    File.open(filename, "rb") { |f|
      obj = Marshal.load(f)
      return obj;
    }
  end

  def inflate(string)
    zstream = Zlib::Inflate.new
    buf = zstream.inflate(string)
    zstream.finish
    zstream.close
    buf
  end
end