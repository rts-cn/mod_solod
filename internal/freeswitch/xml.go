package freeswitch

import (
	"solod.dev/so/c"
)

//so:extern
type switch_xml_node_t struct{}
type XML switch_xml_node_t // *(switch_xml_t) xml element
type XMLRoot struct {
	root *XML
}

//so:extern
func switch_xml_open_cfg(file_path string, node **XML, params *switch_event_t) *XML

//so:extern
func switch_xml_child(xml *XML, name string) *XML

//so:extern
func switch_xml_attr(xml *XML, attr string) string

//so:extern
func switch_xml_attr_soft(xml *XML, attr string) *char

//so:extern
func switch_xml_free(xml *XML)

//so:extern
func switch_xml_next(xml *XML) *XML

func (xml XMLRoot)OpenConfig(file string) *XML {
	var cfg *XML
	xml.root = switch_xml_open_cfg(file, &cfg, nil)
	return cfg
}
func (xml XMLRoot) Free() {
	if xml.root != nil {
		switch_xml_free(xml.root)
		xml.root = nil
	}
}

func (xml *XML) Next() *XML {
	return switch_xml_next(xml)
}

func (xml *XML) Child(name string) *XML {
	return switch_xml_child(xml, name)
}

func (xml *XML) Attr(attr string) string {
	val := switch_xml_attr_soft(xml, attr)
	return c.String((*byte)(val))
}
