function data = read_idx(filename)
% READ_IDX  Nacita subor vo formate IDX (MNIST binarny format)
%   images = read_idx('images.idx3-ubyte')  -> [H x W x N] uint8
%   labels = read_idx('labels.idx1-ubyte')  -> [N x 1] uint8

fid = fopen(filename, 'rb', 'ieee-be');   % big-endian
if fid == -1
    error('Nepodarilo sa otvorit subor: %s', filename);
end

magic = fread(fid, 1, 'int32');  

switch magic
    case 2051   % obrazky  [28 x 28 x N]
        N = fread(fid, 1, 'int32');
        H = fread(fid, 1, 'int32');
        W = fread(fid, 1, 'int32');
        raw  = fread(fid, N*H*W, 'uint8=>uint8');
        data = reshape(raw, [W H N]);        % [W x H x N]
        data = permute(data, [2 1 3]);       % [H x W x N]  = [28 x 28 x N]

    case 2049   % labely  [N x 1]
        N    = fread(fid, 1, 'int32');
        data = fread(fid, N, 'uint8=>uint8');

    otherwise
        error('Neznamy magic number: %d', magic);
end

fclose(fid);
end
