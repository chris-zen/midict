//extern crate core_midi;
extern crate core_foundation;
extern crate coremidi_sys;
extern crate time;
extern crate libc;

use core_foundation::string::CFString;
use core_foundation::base::TCFType;

use coremidi_sys::{
    MIDITimeStamp, MIDIPacketList, MIDIPacketListInit, MIDIPacket,
    MIDIClientRef, MIDIClientCreate, MIDIClientDispose,
    MIDIEndpointRef, MIDISourceCreate, MIDIReceived };

use std::time::Duration;
use std::thread;
use std::ptr;
use std::mem;

fn main() {
    let midi_client_name = CFString::new("midict1");
    // let nop = |_| {};
    // let mut midi_client = core_midi::Client::new(&midi_client_name, &nop);
    // let midi_endpoint = midi_client.create_source(&midi_client_name);
    // let note = core_midi::Note(64 as i8);
    // let packet = core_midi::Packet {
    //     time_stamp: Timespec::new(0, 0),
    //     message: core_midi::Message::NoteDown(note, 127)
    // };

    println!("{:?}", midi_client_name);

    let mut midi_client: MIDIClientRef = unsafe { mem::uninitialized() };
    let status = unsafe { MIDIClientCreate(
        midi_client_name.as_concrete_TypeRef(),
        None, ptr::null_mut(),
        &mut midi_client)
    };

    println!("{:?} {:?}", status, midi_client);

    let mut midi_endpoint: MIDIEndpointRef = unsafe { mem::uninitialized() };
    let status = unsafe { MIDISourceCreate(
        midi_client,
        midi_client_name.as_concrete_TypeRef(),
        &mut midi_endpoint)
    };

    println!("{:?} {:?}", status, midi_endpoint);

    // let timestamp: MIDITimeStamp = 0;
    let mut packet = MIDIPacket {
        timeStamp: 0, length: 3, data: [0; 256]
    };
    packet.data[0] = 0x90;
    packet.data[1] = 64;
    packet.data[2] = 0x7f;
    let packet_list = MIDIPacketList {
        numPackets: 0,
        packet: [packet]
    };
    // let packet = unsafe { MIDIPacketListInit(&mut packet_list) };

    // thread::sleep(Duration::from_millis(10000));

    for i in 0..1000 {
        println!("Sending ...");

        let status = unsafe { MIDIReceived(midi_endpoint, &packet_list) };

        thread::sleep(Duration::from_millis(1000));
    }

    let status = unsafe { MIDIClientDispose(midi_client) };
}
