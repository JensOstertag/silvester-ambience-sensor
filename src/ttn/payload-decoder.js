function Decoder(bytes, port) {
    let decoded = {};

    for(let i = 0; i < bytes.length;) {
        let arrayBuffer = new ArrayBuffer(4);
        let dataView = new DataView(arrayBuffer);

        for(let j = 0; j < 4; j++) {
            dataView.setUint8(j, bytes[i]);
            i++;
        }

        decoded["field" + Math.floor(i / 4)] = dataView.getFloat32(0, true);
    }

    return decoded;
}
